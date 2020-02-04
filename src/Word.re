open Phoneme;

type word = list(phoneme);

let toString = (word: word): string => {
  word
  |> List.map((phoneme: phoneme) => {phoneme.sound})
  |> List.fold_right((phoneme, acc) => {phoneme ++ acc}, _, "") /* }*/ /*   word |> String.split_on_char(',') |> List.map (Phoneme.fromString*/;
} /* let fromString = (word: string): word => */;