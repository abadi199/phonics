open Phoneme;

type state = {phonemes: list(phoneme)};

let str = React.string;

type action =
  | NoOp;

let reducer = (state, action) => {
  switch (action) {
  | NoOp => state
  };
};

[@react.component]
let make = (~dispatch, ~state, ~onEditButtonClicked) => {
  module ViewPhonemes = {
    [@react.component]
    let make = (~phonemes) => {
      <div className="phonemes">
        {phonemes
         |> List.mapi((index, phoneme) =>
              <Phoneme phoneme key={string_of_int(index)} />
            )
         |> Array.of_list
         |> React.array}
      </div>;
    };
  };

  <div className="view">
    <ViewPhonemes phonemes={state.phonemes} />
    <button
      className="transparent-button edit-button"
      onClick={_evt => onEditButtonClicked()}
      title="Edit"
    />
  </div>;
};