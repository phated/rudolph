let build = () => {
  open Rollup;

  let inputOptions = InputOptions.make(~input="index.js");
  let outputOptions = OutputOptions.make(~format="iife", ~file="output.js");

  rollup(inputOptions)
  ->Future.flatMapOk(bundle => Bundle.generate(bundle, outputOptions))
  ->Future.mapOk(output =>
      Belt.Array.keep(Output.outputGet(output), chunk =>
        Chunk.isEntry(chunk)
      )
    )
  /* TODO: fix array access */
  ->Future.mapOk(chunks => Chunk.codeGet(chunks[0]));
};

/* let default = Micro.make((req, res) => build()); */

type stream;
type opts;

[@bs.deriving abstract]
type methods = {createReadStream: (string, opts) => stream};

[@bs.module]
external handler:
  (
    Http.IncomingMessage.t,
    Http.ServerResponse.t,
    Js.Nullable.t(unit),
    methods
  ) =>
  unit =
  "serve-handler";

[@bs.module]
external html:
  {
    .
    "title": string,
    "entry": string,
  } =>
  stream =
  "simple-html-index";

let server =
  Http.createServer((request, response) =>
    handler(
      request,
      response,
      Js.Nullable.undefined,
      methods(~createReadStream=(path, config) =>
        html({"title": "test", "entry": "bundle.js"})
      ),
    )
  );

Http.Server.listen(server, 3000, () =>
  Js.log("Running at http://localhost:3000")
);
