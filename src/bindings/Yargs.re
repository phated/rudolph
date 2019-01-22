type yargs;

module Options = {
  [@bs.deriving abstract]
  type t = {
    [@bs.as "type"]
    type_: string,
  };

  let make = t;
};

[@bs.module "yargs"] external yargs: yargs = "default";

[@bs.send] external option: (yargs, string, Options.t) => yargs = "";
let option = (string, options) => option(string, options);

[@bs.get] external argv: yargs => Js.t('result) = "";
