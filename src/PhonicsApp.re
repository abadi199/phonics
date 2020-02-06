type state =
  | Edit(Edit.state)
  | View(View.state);

type action =
  | EditAction(Edit.action)
  | ViewAction(View.action)
  | ViewClicked
  | EditClicked;

let str = React.string;

let toView = (state: state) => {
  switch (state) {
  | Edit(editState) => View({word: editState.word})
  | View(_) => state
  };
};

let toEdit = (state: state) => {
  switch (state) {
  | View(viewState) =>
    Edit({
      activeIndex: 0,
      word: viewState.word,
      display: Edit.DisplayPhonemeSelection,
    })
  | Edit(_) => state
  };
};

[@react.component]
let make = () => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) => {
        switch (action, state) {
        | (EditAction(editAction), Edit(editState)) =>
          Edit(Edit.reducer(editState, editAction))
        | (ViewAction(viewAction), View(viewState)) =>
          View(View.reducer(viewState, viewAction))
        | (ViewClicked, _) => toView(state)
        | (EditClicked, _) => toEdit(state)
        | _ => state
        }
      },
      Edit(Edit.initialState),
    );
  <div className="app">
    {switch (state) {
     | Edit(editState) =>
       <Edit
         state=editState
         dispatch={editAction => dispatch(EditAction(editAction))}
         onViewButtonClicked={() => dispatch(ViewClicked)}
       />
     | View(viewState) =>
       <View
         state=viewState
         dispatch={viewAction => dispatch(ViewAction(viewAction))}
         onEditButtonClicked={() => dispatch(EditClicked)}
       />
     }}
  </div>;
};