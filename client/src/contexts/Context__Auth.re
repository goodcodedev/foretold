open Rationale.Function.Infix;
type error = string;

module Jwt = {
  type jwt = Js_dict.t(Js.Json.t);

  [@bs.module] external decode: string => Js.Json.t = "jwt-decode";

  let get_attribute = (attribute: string, jwt: jwt) =>
    Js.Dict.get(jwt, attribute) |> E.O.bind(_, Js.Json.decodeString);

  let make = (s: string) => s |> decode |> Js.Json.decodeObject;
};

module AuthTokens = {
  type access_token = string;
  type id_token = string;
  type expires_at = string;

  type t = {
    access_token,
    id_token,
    expires_at,
  };

  let jwt = (t: t) => Jwt.make(t.id_token);
  let auth0Id = (t: t) => t |> jwt |> E.O.bind(_, Jwt.get_attribute("sub"));

  let set = (t: t) => {
    open Dom.Storage;
    localStorage |> setItem("access_token", t.access_token);
    localStorage |> setItem("id_token", t.id_token);
    localStorage |> setItem("expires_at", t.expires_at);
    ();
  };

  let destroy = () => {
    open Dom.Storage;
    localStorage |> removeItem("access_token");
    localStorage |> removeItem("id_token");
    localStorage |> removeItem("expires_at");
    ();
  };

  let exists = (t: option(t)) => E.O.isSome(t);

  let isObsolete = (t: t) => {
    let exp = t.expires_at;
    let isExpired =
      Int64.of_string ||> Int64.to_float ||> (e => e < E.JsDate.now());
    exp |> isExpired;
  };

  let make_from_storage = () => {
    open Dom.Storage;
    let get = e => localStorage |> getItem(e);
    switch (get("access_token"), get("id_token"), get("expires_at")) {
    | (Some(a), Some(b), Some(c)) =>
      Some({access_token: a, id_token: b, expires_at: c})
    | _ => None
    };
  };

  let make = (access_token, id_token, expires_at) => {
    access_token,
    id_token,
    expires_at,
  };
};

module Auth0Client = {
  type t = {. "authorize": [@bs.meth] (unit => unit)};
  type clientOptions = {
    .
    "domain": string,
    "clientID": string,
    "redirectUri": string,
    "responseType": string,
    "scope": string,
  };

  [@bs.module "auth0-js"] [@bs.new]
  external createClient: clientOptions => t = "WebAuth";

  let authOptions = {
    "domain": Env.auth0Domain,
    "clientID": Env.auth0ClientId,
    "redirectUri": Env.redirectUrl,
    "responseType": "token id_token",
    "scope": "openid",
  };

  let triggerLoginScreen = () =>
    authOptions |> createClient |> (c => c##authorize());
};

module CallbackUrlToAuthTokens = {
  open Belt;
  open Utils;

  let matchAccessToken = [%re "/access_token=([^\$&]+)/g"];
  let matchExpiresIn = [%re "/expires_in=([^\$&]+)/g"];
  let matchIdToken = [%re "/id_token=([^\$&]+)/g"];

  let make = (url: ReasonReact.Router.url) => {
    let accessToken = url.hash |> resolveRegex(matchAccessToken);
    let idToken = url.hash |> resolveRegex(matchIdToken);
    let expiresIn = url.hash |> resolveRegex(matchExpiresIn);
    let addedMs = expiresIn |> float_of_string |> (e => e *. 1000.);
    let currentTimeMs = E.JsDate.make() |> E.JsDate.valueOf;
    let expiresAtInMs = currentTimeMs +. addedMs;
    let expiresAt = expiresAtInMs |> Int64.of_float |> Int64.to_string;

    switch (accessToken, idToken, expiresAt) {
    | ("", _, _) => None
    | (_, "", _) => None
    | (_, _, "") => None
    | _ => Some(AuthTokens.make(accessToken, idToken, expiresAt))
    };
  };
};

module Actions = {
  let logout = () => {
    AuthTokens.destroy();
    ReasonReact.Router.push("/");
    ();
  };

  let logoutIfTokenIsObsolete = (tokens: AuthTokens.t) =>
    if (tokens |> AuthTokens.isObsolete) {
      logout();
    };
};