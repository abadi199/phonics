open Word;

type state = {word};

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
  module ViewWord = {
    [@react.component]
    let make = (~word) => {
      <div className="word">
        {word
         |> List.mapi((index, phoneme) =>
              <Phoneme phoneme key={string_of_int(index)} />
            )
         |> Array.of_list
         |> React.array}
      </div>;
    };
  };

  <div className="view">
    <ViewWord word={state.word} />
    <button
      className="transparent-button edit-button"
      onClick={_evt => onEditButtonClicked()}
      title="Edit"
    />
  </div>;
};