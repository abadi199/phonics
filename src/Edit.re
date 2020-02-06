open Phoneme;
open Word;

type display =
  | DisplayPhonemeSelection
  | DisplaySavedWords;

type state = {
  word,
  activeIndex: int,
  display,
};

let initialState = {
  word: [Phoneme.a],
  activeIndex: 0,
  display: DisplayPhonemeSelection,
};

let str = React.string;
type action =
  | AddPhoneme
  | RemovePhoneme
  | PhonemeClicked(int, phoneme)
  | SetActive(int)
  | SelectionClicked(phoneme)
  | LoadButtonClicked
  | CloseSavedWordsClicked
  | LoadWord(word);

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
      activeIndex: List.length(state.word),
      word: state.word @ [Phoneme.a],
    }
  | RemovePhoneme =>
    if (List.length(state.word) > 1) {
      let newPhonemes = state.word |> List.rev |> List.tl |> List.rev;
      let length = List.length(newPhonemes);
      {
        ...state,
        word: newPhonemes,
        activeIndex:
          List.length(newPhonemes) > state.activeIndex
            ? state.activeIndex : length - 1,
      };
    } else {
      state;
    }
  | PhonemeClicked(index, phoneme) => {
      ...state,
      word: selectPhoneme(index, phoneme, state.word),
    }
  | SetActive(index) => {...state, activeIndex: index}
  | SelectionClicked(clickedPhoneme) => {
      ...state,
      word:
        state.word
        |> List.mapi((index, phoneme) => {
             index == state.activeIndex ? clickedPhoneme : phoneme
           }),
    }
  | LoadButtonClicked => {...state, display: DisplaySavedWords}
  | CloseSavedWordsClicked => {...state, display: DisplayPhonemeSelection}
  | LoadWord(word) => {...state, word}
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

  module ViewWord = {
    [@react.component]
    let make = (~word: list(phoneme)) => {
      <>
        <div className="word">
          {word
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
        <PhonemeSelection />
      </>;
    };
  };

  module ActionSection = {
    let saveWord = () => {
      Storage.saveWord(state.word);
    };

    [@react.component]
    let make = () => {
      <div className="action">
        <button
          className="transparent-button view-button"
          onClick={_evt => onViewButtonClicked()}
          title="Play"
        />
        <button
          className="transparent-button save-button"
          onClick={_evt => saveWord()}
          title="Save"
        />
        <button
          className="transparent-button load-button"
          onClick={_evt => dispatch(LoadButtonClicked)}
          title="Load"
        />
      </div>;
    };
  };
  let loadWord = (word: word) => {
    dispatch(LoadWord(word));
    dispatch(CloseSavedWordsClicked);
  };

  <div className="edit">
    {switch (state.display) {
     | DisplayPhonemeSelection =>
       <> <ViewWord word={state.word} /> <ActionSection /> </>
     | DisplaySavedWords =>
       <SavedWords
         onWordClicked=loadWord
         onCloseClicked={() => dispatch(CloseSavedWordsClicked)}
       />
     }}
  </div>;
};