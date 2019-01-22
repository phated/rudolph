open Http;

let make:
  (
    (IncomingMessage.t, ServerResponse.t) =>
    Future.t(Belt.Result.t('result, exn)),
    IncomingMessage.t,
    ServerResponse.t
  ) =>
  Js.Promise.t('result);
