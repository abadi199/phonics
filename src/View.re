open Word;

type display =
  | DisplayPlay
  | DisplaySavedWords;

type state = {
  word,
  display,
};

let str = React.string;

type action =
  | LoadWord(word)
  | LoadButtonClicked
  | CloseSavedWordsClicked;

let reducer = (state, action) => {
  switch (action) {
  | LoadWord(word) => {word, display: DisplayPlay}
  | LoadButtonClicked => {...state, display: DisplaySavedWords}
  | CloseSavedWordsClicked => {...state, display: DisplayPlay}
  };
};

[@react.component]
let make = (~dispatch, ~state, ~onEditButtonClicked) => {
  module ViewWord = {
    [@react.component]
    let make = (~word) => {
      <div className="word">
        {word
         |> List.mapi((index, phoneme) =>
              <Phoneme phoneme key={string_of_int(index)} />
            )
         |> Array.of_list
         |> React.array}
      </div>;
    };
  };

  module ActionSection = {
    [@react.component]
    let make = () => {
      <div className="action">
        <button
          className="transparent-button load-button"
          onClick={_evt => dispatch(LoadButtonClicked)}
          title="Load"
        />
        <button
          className="transparent-button edit-button"
          onClick={_evt => onEditButtonClicked()}
          title="Edit"
        />
      </div>;
    };
  };

  module Navigation = {
    let prevButtonClicked = _evt => {
      let word = Storage.prevWord(state.word);
      dispatch(LoadWord(word));
    };

    let shuffleButtonClicked = _evt => {
      let word =
        Storage.shuffleWord()->Belt.Option.getWithDefault(state.word);
      dispatch(LoadWord(word));
    };

    let nextButtonClicked = _evt => {
      let word = Storage.nextWord(state.word);
      dispatch(LoadWord(word));
    };

    [@react.component]
    let make = () => {
      <div className="navigation">
        <button
          className="transparent-button prev-button"
          title="Next"
          onClick=prevButtonClicked
        />
        <button
          className="transparent-button shuffle-button"
          title="Next"
          onClick=shuffleButtonClicked
        />
        <button
          className="transparent-button next-button"
          title="Next"
          onClick=nextButtonClicked
        />
      </div>;
    };
  };

  switch (state.display) {
  | DisplayPlay =>
    <div className="play">
      <ViewWord word={state.word} />
      <Navigation />
      <ActionSection />
    </div>
  | DisplaySavedWords =>
    <SavedWords
      onWordClicked={(word: word) => dispatch(LoadWord(word))}
      onCloseClicked={() => dispatch(CloseSavedWordsClicked)}
    />
  };
};