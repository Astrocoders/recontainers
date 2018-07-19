# ReContainers
[![Build Status](https://travis-ci.org/Astrocoders/ReContainers.svg?branch=master)](https://travis-ci.org/Astrocoders/ReContainers)

```
$ yarn add re-containers
```

## Inspired by 

Inspired by [recompose](https://github.com/acdlite/recompose/), [react-powerplug](https://github.com/renatorib/react-powerplug) and [smalldots](https://github.com/smalldots)

# Containers

Available API

## Component
Nice for lifecycle helpers

```reasonml
<Component didMount willUnmount willUpdate>
  ...((self) => {
    <div />
  })
</Component>
```

## Loader

Handling promises

```
module ReLoader = ReContainers.Loader.Make({
  /* Promise result */
  type t = int;
});
```

```reasonml
let makeTimeout = () =>
  Js.Promise.make((~resolve, ~reject as _) =>
    Js.Global.setTimeout(() => resolve(. 0), 2000) |> ignore
  );

<ReLoader>
  ...(
       (~state, ~load, ~reset as _) =>
         <div className="App">
           <div className="App-header">
             <img src=logo className="App-logo" alt="logo" />
             <h2> (ReasonReact.string(message)) </h2>
             <button onClick=(_e => load(makeTimeout()))>
               (ReasonReact.string("Click me"))
             </button>
           </div>
           (
             switch (state) {
             | Loading =>
               <p> (ReasonReact.string("Hang a sec")) </p>
             | Error(string) => <p> (ReasonReact.string(string)) </p>
             | Success(_promiseResult) => <p> (ReasonReact.string("All good")) </p>
             | Empty => ReasonReact.null
             }
           )
         </div>
     )
</ReLoader>
```
