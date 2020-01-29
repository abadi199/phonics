type phoneme = {
  sound: string,
  image: string,
};

let emptyPhoneme = {sound: "..", image: ""};
let phonemes: list(phoneme) = [
  {sound: "A", image: ""},
  {sound: "B", image: ""},
  {sound: "C", image: ""},
  {sound: "D", image: ""},
  {sound: "E", image: ""},
];

let str = React.string;

[@react.component]
let make = (~phoneme) => {
  <div className="phoneme"> {str(phoneme.sound)} </div>;
};