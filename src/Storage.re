open Word;

let storageKey = "phonemes";

let fromString = (words: string): list(word) => {
  words
  |> String.split_on_char('|')
  |> List.filter(s => s != "")
  |> List.map(Word.fromString);
};

let toString = (words: list(word)) => {
  words
  |> List.fold_left(
       (acc, word) => {acc ++ (acc == "" ? "" : "|") ++ Word.toString(word)},
       "",
     );
};

module WordCompare =
  Belt.Id.MakeComparable({
    type t = word;
    let cmp = (a: word, b: word) =>
      compare(Word.toString(a), Word.toString(b));
  });

let addWord: (option(string), word) => string =
  (existingWords, word) => {
    let existingWordSet =
      existingWords
      |> Belt.Option.mapWithDefault(_, [], a => fromString(a))
      |> List.fold_left(
           (set, word) => {Belt.Set.add(set, word)},
           Belt.Set.make(~id=(module WordCompare)),
           _,
         );
    let updatedWordSet = existingWordSet |> Belt.Set.add(_, word);
    let wordList: list(word) = updatedWordSet |> Belt.Set.toList;
    toString(wordList);
  };

let saveWord = (word: word) => {
  let existingWords =
    Dom.Storage.getItem(storageKey, Dom.Storage.localStorage);
  let updatedWords = addWord(existingWords, word);
  Dom.Storage.setItem(storageKey, updatedWords, Dom.Storage.localStorage);
};

let removeWord: (option(string), word) => string =
  (existingWords, word) => {
    let existingWordSet =
      existingWords
      |> Belt.Option.mapWithDefault(_, [], a => fromString(a))
      |> List.fold_left(
           (set, word) => {Belt.Set.add(set, word)},
           Belt.Set.make(~id=(module WordCompare)),
           _,
         );
    let updatedWordSet = existingWordSet |> Belt.Set.remove(_, word);
    let wordList: list(word) = updatedWordSet |> Belt.Set.toList;
    toString(wordList);
  };

let loadWords: unit => list(word) =
  () => {
    Dom.Storage.getItem(storageKey, Dom.Storage.localStorage)
    |> Belt.Option.mapWithDefault(_, [], fromString);
  };

let deleteWord: word => list(word) =
  word => {
    let existingWords =
      Dom.Storage.getItem(storageKey, Dom.Storage.localStorage);
    let updatedWords = removeWord(existingWords, word);
    Dom.Storage.setItem(storageKey, updatedWords, Dom.Storage.localStorage);
    loadWords();
  };