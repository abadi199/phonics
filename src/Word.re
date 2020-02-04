open Phoneme;

type word = list(phoneme);

let toString = (word: word): string => {
  word
  |> List.map((phoneme: phoneme) => {phoneme.sound})
  |> List.fold_right((phoneme, acc) => {phoneme ++ acc}, _, "");
};