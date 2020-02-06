open Jest;
open Phoneme;

describe("Word", () => {
  describe("toString", () => {
    open Expect;
    test("toString(m,a,t)", () =>
      expect([m, a, t] |> Word.toString) |> toBe("m,a,t")
    );

    test("toString(qu,i,c,k)", () =>
      expect([qu, i, c, k] |> Word.toString) |> toBe("qu,i,c,k")
    );
  });

  describe("fromString", () => {
    open Expect;
    test("fromString(\"m,a,t\")", () =>
      expect("m,a,t" |> Word.fromString) |> toEqual([m, a, t])
    );

    test("fromString(\"qu,i,c,k\")", () =>
      expect("qu,i,c,k" |> Word.fromString) |> toEqual([qu, i, c, k])
    );
  });
});