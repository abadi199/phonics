open Phoneme;

type state = {
  phonemes: list(phoneme),
  activeIndex: int,
};

let initialState = {phonemes: [firstPhoneme], activeIndex: 0};

let str = React.string;

type action =
  | AddPhoneme
  | RemovePhoneme
  | PhonemeClicked(int, phoneme)
  | SetActive(int)
  | SelectionClicked(phoneme);

type accumulator('a) = {
  list: list('a),
  found: bool,
};

let selectPhoneme = (index, phoneme, list) =>
  list |> List.mapi((i, element) => i == index ? phoneme : element);

let reducer = (state, action) => {
  switch (action) {
  | AddPhoneme => {...state, phonemes: state.phonemes @ [firstPhoneme]}
  | RemovePhoneme =>
    if (List.length(state.phonemes) > 1) {
      let newPhonemes = state.phonemes |> List.rev |> List.tl |> List.rev;
      let length = List.length(newPhonemes);
      {
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
        </div>
      </>;
    };
  };

  <div className="edit">
    <ViewPhonemes phonemes={state.phonemes} />
    <button
      className="view-button"
      onClick={_evt => onViewButtonClicked()}
      title="Play"
    />
  </div>;
};