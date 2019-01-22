module IncomingMessage = {
  type t;

  [@bs.get] external url: t => string = "";
};

module ServerResponse = {
  type t;
};

module Server = {
  type t;

  [@bs.send] external listen: (t, int, unit => unit) => unit = "";
};

[@bs.module "http"]
external createServer:
  ((IncomingMessage.t, ServerResponse.t) => unit) => Server.t =
  "";
