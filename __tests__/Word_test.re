open Jest;
open Phoneme;

describe("Word", () => {
  describe("toString", () => {
    open Expect;
    test("toString(m,a,t)", () =>
      expect([m, a, t] |> Word.toString) |> toBe("m,a,t")
    );

    test("toString(qu,i,ck)", () =>
      expect([qu, i, ck] |> Word.toString) |> toBe("qu,i,ck")
    );
  });

  describe("fromString", () => {
    open Expect;
    test("fromString(\"m,a,t\")", () =>
      expect("m,a,t" |> Word.fromString) |> toEqual([m, a, t])
    );

    test("fromString(\"qu,i,c,k\")", () =>
      expect("qu,i,ck" |> Word.fromString) |> toEqual([qu, i, ck])
    );
  });

  describe("findPrev", () => {
    Expect.(
      test("findPrev", () =>
        expect(
          Word.findPrev([[m, a, t], [qu, i, ck]], [qu, i, ck])
          ->Belt.Option.map(Word.toString),
        )
        |> toEqual(Some("m,a,t"))
      )
    )
  });

  describe("findNext", () => {
    Expect.(
      test("findNext", () =>
        expect(
          Word.findNext([[m, a, t], [qu, i, ck]], [m, a, t])
          ->Belt.Option.map(Word.toString),
        )
        |> toEqual(Some("qu,i,ck"))
      )
    )
  });
});