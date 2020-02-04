open Phoneme;

let storageKey = "phonemes";

type drawer =
  | PhonemeSelection
  | SavedWords;

type state = {
  phonemes: list(phoneme),
  activeIndex: int,
  drawer,
};

let initialState = {
  phonemes: [firstPhoneme],
  activeIndex: 0,
  drawer: PhonemeSelection,
};

let str = React.string;

type action =
  | AddPhoneme
  | RemovePhoneme
  | PhonemeClicked(int, phoneme)
  | SetActive(int)
  | SelectionClicked(phoneme)
  | LoadButtonClicked
  | CloseSavedWordsClicked;

type accumulator('a) = {
  list: list('a),
  found: bool,
};

let selectPhoneme = (index, phoneme, list) =>
  list |> List.mapi((i, element) => i == index ? phoneme : element);

let reducer = (state, action) => {
  switch (action) {
  | AddPhoneme => {
      ...state,
      activeIndex: List.length(state.phonemes),
      phonemes: state.phonemes @ [firstPhoneme],
    }
  | RemovePhoneme =>
    if (List.length(state.phonemes) > 1) {
      let newPhonemes = state.phonemes |> List.rev |> List.tl |> List.rev;
      let length = List.length(newPhonemes);
      {
        ...state,
        phonemes: newPhonemes,
        activeIndex:
          List.length(newPhonemes) > state.activeIndex
            ? state.activeIndex : length - 1,
      };
    } else {
      state;
    }
  | PhonemeClicked(index, phoneme) => {
      ...state,
      phonemes: selectPhoneme(index, phoneme, state.phonemes),
    }
  | SetActive(index) => {...state, activeIndex: index}
  | SelectionClicked(clickedPhoneme) => {
      ...state,
      phonemes:
        state.phonemes
        |> List.mapi((index, phoneme) => {
             index == state.activeIndex ? clickedPhoneme : phoneme
           }),
    }
  | LoadButtonClicked => {...state, drawer: SavedWords}
  | CloseSavedWordsClicked => {...state, drawer: PhonemeSelection}
  };
};

[@react.component]
let make = (~state, ~dispatch, ~onViewButtonClicked) => {
  module SelectedPhoneme = {
    [@react.component]
    let make = (~selectedPhoneme as phoneme, ~active, ~onClick) => {
      <div className={"selected" ++ (active ? " active" : "")}>
        <Phoneme phoneme onClick />
      </div>;
    };
  };

  module PhonemeSelection = {
    [@react.component]
    let make = () => {
      <div className="selection">
        {Phoneme.phonemes
         |> List.mapi((index, phoneme) =>
              <Phoneme
                phoneme
                key={string_of_int(index)}
                onClick={() => dispatch(SelectionClicked(phoneme))}
              />
            )
         |> Array.of_list
         |> React.array}
      </div>;
    };
  };

  module SavedWords = {
    [@react.component]
    let make = () => {
      let (savedWords, setSavedWords) = React.useState(() => "");
      React.useEffect1(
        () => {
          setSavedWords(_ =>
            Dom.Storage.getItem(storageKey, Dom.Storage.localStorage)
            ->Belt.Option.getWithDefault("fail")
          );
          None;
        },
        [||],
      );
      <div className="saved-words">
        {str(savedWords)}
        <button
          className="transparent-button close-button"
          onClick={_evt => dispatch(CloseSavedWordsClicked)}
          title="Close"
        />
      </div>;
    };
  };

  module ViewPhonemes = {
    [@react.component]
    let make = (~phonemes: list(phoneme)) => {
      <>
        <div className="phonemes">
          {phonemes
           |> List.mapi((index, selectedPhoneme) =>
                <SelectedPhoneme
                  selectedPhoneme
                  active={index == state.activeIndex}
                  key={string_of_int(index)}
                  onClick={() => dispatch(SetActive(index))}
                />
              )
           |> Array.of_list
           |> React.array}
          <button
            className="remove-phoneme"
            onClick={_evt => dispatch(RemovePhoneme)}>
            {str("-")}
          </button>
          <button
            className="add-phoneme" onClick={_evt => dispatch(AddPhoneme)}>
            {str("+")}
          </button>
        </div>
        {switch (state.drawer) {
         | PhonemeSelection => <PhonemeSelection />
         | SavedWords => <SavedWords />
         }}
      </>;
    };
  };

  let save = () => {
    Dom.Storage.setItem(storageKey, "test 123", Dom.Storage.localStorage);
  };

  <div className="edit">
    <ViewPhonemes phonemes={state.phonemes} />
    <div className="action">
      <button
        className="transparent-button view-button"
        onClick={_evt => onViewButtonClicked()}
        title="Play"
      />
      <button
        className="transparent-button save-button"
        onClick={_evt => save()}
        title="Save"
      />
      <button
        className="transparent-button load-button"
        onClick={_evt => dispatch(LoadButtonClicked)}
        title="Load"
      />
    </div>
  </div>;
};