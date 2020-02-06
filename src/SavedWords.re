[@react.component]
let make = (~onWordClicked, ~onCloseClicked) => {
  let (savedWords, setSavedWords) = React.useState(() => []);

  let deleteWord = (word: Word.word) => {
    let words = Storage.deleteWord(word);
    Js.log(Storage.toString(words));
    setSavedWords(_ => words);
  };

  React.useEffect1(
    () => {
      setSavedWords(_ => Storage.loadWords());
      None;
    },
    [||],
  );
  <div className="saved-words">
    {savedWords
     |> List.map(word =>
          <Word
            word
            key={Word.toString(word)}
            onDeleteClicked={() => deleteWord(word)}
            onClick={() => onWordClicked(word)}
          />
        )
     |> Array.of_list
     |> React.array}
    <button
      className="transparent-button close-button"
      onClick={_evt => onCloseClicked()}
      title="Close"
    />
  </div>;
};