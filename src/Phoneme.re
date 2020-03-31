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

let a = {sound: "a", image: "", color: Orange, side: Front};
let m = {sound: "m", image: "", color: Orange, side: Front};
let s = {sound: "s", image: "", color: Orange, side: Front};
let d = {sound: "d", image: "", color: Orange, side: Front};
let t = {sound: "t", image: "", color: Orange, side: Front};
let orange: list(phoneme) = [a, m, s, d, t];

let i = {sound: "i", image: "", color: Purple, side: Front};
let n = {sound: "n", image: "", color: Purple, side: Front};
let p = {sound: "p", image: "", color: Purple, side: Front};
let g = {sound: "g", image: "", color: Purple, side: Front};
let o = {sound: "o", image: "", color: Purple, side: Front};
let purple: list(phoneme) = [i, n, p, g, o];

let c = {sound: "c", image: "", color: Yellow, side: Front};
let k = {sound: "k", image: "", color: Yellow, side: Front};
let u = {sound: "u", image: "", color: Yellow, side: Front};
let b = {sound: "b", image: "", color: Yellow, side: Front};
let yellow: list(phoneme) = [c, k, u, b];

let f = {sound: "f", image: "", color: Grey, side: Front};
let e = {sound: "e", image: "", color: Grey, side: Front};
let l = {sound: "l", image: "", color: Grey, side: Front};
let h = {sound: "h", image: "", color: Grey, side: Front};
let sh = {sound: "sh", image: "", color: Grey, side: Front};
let grey: list(phoneme) = [f, e, l, h, sh];

let r = {sound: "r", image: "", color: Pink, side: Front};
let j = {sound: "j", image: "", color: Pink, side: Front};
let v = {sound: "v", image: "", color: Pink, side: Front};
let y = {sound: "y", image: "", color: Pink, side: Front};
let w = {sound: "w", image: "", color: Pink, side: Front};
let pink: list(phoneme) = [r, j, v, y, w];

let th = {sound: "th", image: "", color: Blue, side: Front};
let z = {sound: "z", image: "", color: Blue, side: Front};
let ch = {sound: "ch", image: "", color: Blue, side: Front};
let ck = {sound: "ck", image: "", color: Blue, side: Front};
let qu = {sound: "qu", image: "", color: Blue, side: Front};
let x = {sound: "x", image: "", color: Blue, side: Front};
let ng = {sound: "ng", image: "", color: Blue, side: Front};
let nk = {sound: "nk", image: "", color: Blue, side: Front};
let blue: list(phoneme) = [th, z, ch, ck, qu, x, ng, nk];

let phonemes: list(phoneme) = orange @ purple @ yellow @ grey @ pink @ blue;

let toString = (phoneme: phoneme): string => phoneme.sound;

let fromString = (sound: string): option(phoneme) => {
  switch (sound) {
  | "a" => Some(a)
  | "m" => Some(m)
  | "s" => Some(s)
  | "d" => Some(d)
  | "t" => Some(t)
  | "i" => Some(i)
  | "n" => Some(n)
  | "p" => Some(p)
  | "g" => Some(g)
  | "o" => Some(o)
  | "c" => Some(c)
  | "k" => Some(k)
  | "u" => Some(u)
  | "b" => Some(b)
  | "f" => Some(f)
  | "e" => Some(e)
  | "l" => Some(l)
  | "h" => Some(h)
  | "sh" => Some(sh)
  | "r" => Some(r)
  | "j" => Some(j)
  | "v" => Some(v)
  | "y" => Some(y)
  | "w" => Some(w)
  | "th" => Some(th)
  | "z" => Some(z)
  | "ch" => Some(ch)
  | "qu" => Some(qu)
  | "x" => Some(x)
  | "ng" => Some(ng)
  | "nk" => Some(nk)
  | _ => None
  };
};

let str = React.string;

[@react.component]
let make = (~phoneme, ~onClick=() => ()) => {
  <div
    className={"phoneme " ++ toClassName(phoneme.color)}
    onClick={_evt => onClick()}>
    {str(phoneme.sound)}
  </div>;
};