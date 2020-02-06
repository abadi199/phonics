open Phoneme;

type word = list(phoneme);

let toString = (word: word): string => {
  word
  |> List.map((phoneme: phoneme) => {phoneme.sound})
  |> List.fold_right(
       (phoneme, acc) => {phoneme ++ (acc == "" ? "" : ",") ++ acc},
       _,
       "",
     );
};

let fromString = (word: string): word => {
  word
  |> String.split_on_char(',')
  |> List.map(Phoneme.fromString)
  |> List.map(Belt.Option.mapWithDefault(_, [], p => [p]))
  |> List.flatten;
};

[@react.component]
let make = (~word: word, ~onDeleteClicked=() => (), ~onClick=() => ()) => {
  <div className="word" onClick={_evt => onClick()}>
    {word
     |> List.mapi((index, phoneme) =>
          <Phoneme phoneme key={string_of_int(index)} />
        )
     |> Array.of_list
     |> React.array}
    <button
      className="delete-word-button"
      title="Delete Word"
      onClick={_evt => {
        ReactEvent.Mouse.stopPropagation(_evt);
        onDeleteClicked();
      }}
    />
  </div>;
};