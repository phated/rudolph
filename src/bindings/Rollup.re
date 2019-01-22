exception OutputGenerationError;
exception BundleGenerationError;

module InputOptions = {
  [@bs.deriving abstract]
  type t = {input: string};

  let make = t;
};

module OutputOptions = {
  [@bs.deriving abstract]
  type t = {
    format: string,
    file: string,
  };
  let make = t;
};

module Chunk = {
  [@bs.deriving abstract]
  type t = {
    code: string,
    isEntry: bool,
  };

  let make = t;

  let isEntry = isEntryGet;
};

module Output = {
  [@bs.deriving abstract]
  type t = {output: array(Chunk.t)};
};

module Bundle = {
  type t;

  [@bs.send]
  external generate: (t, OutputOptions.t) => Js.Promise.t(Output.t) = "";
  let generate = (bundle, outputOptions) =>
    FutureJs.fromPromise(generate(bundle, outputOptions), _err =>
      OutputGenerationError
    );
};

[@bs.module "rollup"]
external rollup: InputOptions.t => Js.Promise.t(Bundle.t) = "";
let rollup = options =>
  FutureJs.fromPromise(rollup(options), _err => BundleGenerationError);
