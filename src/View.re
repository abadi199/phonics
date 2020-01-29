open Phoneme;

type state = {phonemes: list(phoneme)};

let str = React.string;

[@react.component]
let make = (~editButtonClicked) => {
  <div className="view">
    {str("View 2.0")}
    <button onClick={_evt => editButtonClicked()}> {str("Edit")} </button>
  </div>;
};