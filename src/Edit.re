open Phoneme;

type state = {phonemes: list(phoneme)};

let initialState = {phonemes: [firstPhoneme]};

let str = React.string;

type action =
  | AddPhoneme
  | RemovePhoneme
  | PhonemeClicked(int, phoneme);

type accumulator('a) = {
  list: list('a),
  found: bool,
};

let findAfter = (element: 'a, list: list('a)): list('a) => {
  let result: accumulator('a) =
    List.fold_right(
      (current: 'a, accumulator: accumulator('a)) =>
        if (current == element) {
          {...accumulator, found: true};
        } else if (accumulator.found) {
          accumulator;
        } else {
          {...accumulator, list: [current, ...accumulator.list]};
        },
      list,
      {list: [], found: false},
    );

  result.list;
};

let findBefore = (element: 'a, list: list('a)): list('a) => {
  let result: accumulator('a) =
    List.fold_left(
      (accumulator: accumulator('a), current: 'a) =>
        if (current.sound === element.sound) {
          {...accumulator, found: true};
        } else if (accumulator.found) {
          accumulator;
        } else {
          {...accumulator, list: [current, ...accumulator.list]};
        },
      {list: [], found: false},
      list,
    );

  result.list |> List.rev;
};

let selectPhoneme = (index, phoneme, list) =>
  list |> List.mapi((i, element) => i == index ? phoneme : element);

let reducer = (state, action) => {
  switch (action) {
  | AddPhoneme => {phonemes: state.phonemes @ [firstPhoneme]}
  | RemovePhoneme => {
      phonemes: state.phonemes |> List.rev |> List.tl |> List.rev,
    }
  | PhonemeClicked(index, phoneme) => {
      phonemes: selectPhoneme(index, phoneme, state.phonemes),
    }
  };
};

[@react.component]
let make = (~state, ~dispatch, ~onViewButtonClicked) => {
  module PhonemeSelector = {
    [@react.component]
    let make = (~selectedPhoneme as phoneme, ~index) => {
      let before: list(phoneme) = phonemes |> findBefore(phoneme);
      let after: list(phoneme) = phonemes |> findAfter(phoneme);
      <div className="phoneme-selector">
        <div className="before">
          {before
           |> List.mapi((beforeIndex, beforePhoneme) =>
                <Phoneme
                  key={string_of_int(beforeIndex)}
                  phoneme=beforePhoneme
                  onClick={() =>
                    dispatch(PhonemeClicked(index, beforePhoneme))
                  }
                />
              )
           |> Array.of_list
           |> React.array}
        </div>
        <div className="selected"> <Phoneme phoneme /> </div>
        <div className="after">
          {after
           |> List.mapi((afterIndex, afterPhoneme) =>
                <Phoneme
                  key={string_of_int(afterIndex)}
                  phoneme=afterPhoneme
                  onClick={() =>
                    dispatch(PhonemeClicked(index, afterPhoneme))
                  }
                />
              )
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
         |> List.mapi((index, selectedPhoneme) =>
              <PhonemeSelector
                selectedPhoneme
                index
                key={string_of_int(index)}
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
      </div>;
    };
  };

  <div className="edit">
    <ViewPhonemes phonemes={state.phonemes} />
    <button className="edit-button" onClick={_evt => onViewButtonClicked()}>
      {str("Play")}
    </button>
  </div>;
};