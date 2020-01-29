open Phoneme;

type state = {phonemes: list(phoneme)};

let initialState = {phonemes: [emptyPhoneme]};

let str = React.string;

type action =
  | AddPhoneme;

let findBefore = (element, list) => {
  List.fold_right((current, accummulator) => {
    if (current === element) {
      { ...accummulator, found: true };
    } else if (found) {
      accummulator;
    } else {
      { ...accummulator, list: [current, ...accummulator.list] };
    }
  }, list, {list: [], found: false});
};

let findAfter = (element, list) => {
  List.fold_left((current, accummulator) => {
    if (current === element) {
      { ...accummulator, found : true }
    } else if (found) {
      accummulator
    } else {
      { ...accummulator, list: [ current, ...accummulator.list] }
    }
  }, list, {list: [], found: false}));
};

[@react.component]
let make = (~viewButtonClicked) => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) => {
        switch (action) {
        | AddPhoneme => {phonemes: [emptyPhoneme, ...state.phonemes]}
        }
      },
      initialState,
    );

  module PhonemeSelector = {
    [@react.component]
    let make = (~selectedPhoneme as phoneme) => {
      let before = phonemes |> findBefore(phoneme);
      let after = phonemes |> findAfter(phoneme);
      <div className="phoneme-selector">
        <div className="before">
          {before
           |> List.map(beforePhoneme => <Phoneme phoneme=beforePhoneme />)
           |> Array.of_list
           |> React.array}
        </div>
        <Phoneme phoneme />
        <div className="after">
          {after
           |> List.map(beforePhoneme => <Phoneme phoneme=beforePhoneme />)
           |> Array.of_list
           |> React.array}
        </div>
      </div>;
    };
  };

  module ViewPhonemes = {
    [@react.component]
    let make = (~phonemes: list(phoneme)) => {
      <div className="phonemes">
        {phonemes
         |> List.map(selectedPhoneme => <PhonemeSelector selectedPhoneme />)
         |> Array.of_list
         |> React.array}
        <button onClick={_evt => dispatch(AddPhoneme)}> {str("+")} </button>
      </div>;
    };
  };

  <div className="edit">
    <ViewPhonemes phonemes={state.phonemes} />
    <button onClick={_evt => viewButtonClicked()}> {str("Play")} </button>
  </div>;
};