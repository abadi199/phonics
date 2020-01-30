type color =
  | Orange
  | Purple
  | Yellow
  | Grey
  | Pink
  | Blue;

let toClassName = color => {
  switch (color) {
  | Orange => "orange"
  | Purple => "purple"
  | Yellow => "yellow"
  | Grey => "grey"
  | Pink => "pink"
  | Blue => "blue"
  };
};

type side =
  | Front
  | Back;

type phoneme = {
  sound: string,
  image: string,
  color,
  side,
};

let firstPhoneme = {sound: "a", image: "", color: Orange, side: Front};
let orange: list(phoneme) = [
  firstPhoneme,
  {sound: "m", image: "", color: Orange, side: Front},
  {sound: "s", image: "", color: Orange, side: Front},
  {sound: "d", image: "", color: Orange, side: Front},
  {sound: "t", image: "", color: Orange, side: Front},
];

let purple: list(phoneme) = [
  {sound: "i", image: "", color: Purple, side: Front},
  {sound: "n", image: "", color: Purple, side: Front},
  {sound: "p", image: "", color: Purple, side: Front},
  {sound: "g", image: "", color: Purple, side: Front},
  {sound: "o", image: "", color: Purple, side: Front},
];

let yellow: list(phoneme) = [
  {sound: "c", image: "", color: Yellow, side: Front},
  {sound: "k", image: "", color: Yellow, side: Front},
  {sound: "u", image: "", color: Yellow, side: Front},
  {sound: "b", image: "", color: Yellow, side: Front},
];

let grey: list(phoneme) = [
  {sound: "f", image: "", color: Grey, side: Front},
  {sound: "e", image: "", color: Grey, side: Front},
  {sound: "l", image: "", color: Grey, side: Front},
  {sound: "h", image: "", color: Grey, side: Front},
  {sound: "sh", image: "", color: Grey, side: Front},
];

let pink: list(phoneme) = [
  {sound: "r", image: "", color: Pink, side: Front},
  {sound: "j", image: "", color: Pink, side: Front},
  {sound: "v", image: "", color: Pink, side: Front},
  {sound: "y", image: "", color: Pink, side: Front},
  {sound: "w", image: "", color: Pink, side: Front},
];

let blue: list(phoneme) = [
  {sound: "th", image: "", color: Blue, side: Front},
  {sound: "z", image: "", color: Blue, side: Front},
  {sound: "ch", image: "", color: Blue, side: Front},
  {sound: "qu", image: "", color: Blue, side: Front},
  {sound: "x", image: "", color: Blue, side: Front},
  {sound: "ng", image: "", color: Blue, side: Front},
  {sound: "nk", image: "", color: Blue, side: Front},
];

let phonemes: list(phoneme) = orange @ purple @ yellow @ grey @ pink @ blue;

let str = React.string;

[@react.component]
let make = (~phoneme, ~onClick=() => ()) => {
  <div
    className={"phoneme " ++ toClassName(phoneme.color)}
    onClick={_evt => onClick()}>
    {str(phoneme.sound)}
  </div>;
};