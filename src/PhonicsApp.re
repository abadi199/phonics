type mode =
  | Edit(Edit.state)
  | View(View.state);

type state = {mode};

type action =
  | EditClicked
  | ViewClicked;

let str = React.string;

let toEdit = (mode: mode): mode =>
  switch (mode) {
  | Edit(_) => mode
  | View(viewState) => Edit({phonemes: viewState.phonemes})
  };

let toView = (mode: mode): mode =>
  switch (mode) {
  | Edit(editState) => View({phonemes: editState.phonemes})
  | View(_) => mode
  };

[@react.component]
let make = () => {
  let ({mode}, dispatch) =
    React.useReducer(
      (state, action) => {
        switch (action) {
        | EditClicked => {mode: toEdit(state.mode)}
        | ViewClicked => {mode: toView(state.mode)}
        }
      },
      {mode: Edit(Edit.initialState)},
    );
  <div className="app">
    {switch (mode) {
     | Edit(_) => <Edit viewButtonClicked={() => dispatch(ViewClicked)} />
     | View(_) => <View editButtonClicked={() => dispatch(EditClicked)} />
     }}
  </div>;
};