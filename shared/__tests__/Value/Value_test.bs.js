// Generated by BUCKLESCRIPT VERSION 4.0.5, PLEASE EDIT WITH CARE
'use strict';

var Jest = require("@glennsl/bs-jest/src/jest.js");
var Json = require("@glennsl/bs-json/src/Json.bs.js");
var Block = require("bs-platform/lib/js/block.js");
var Value$Shared = require("../../src/Value/Value.bs.js");

describe("FloatPercentiles", (function () {
        Jest.test("#hasQuartiles true", (function () {
                return Jest.Expect[/* toEqual */12](true, Jest.Expect[/* expect */0](Value$Shared.FloatPercentiles[/* hasQuartiles */2](Value$Shared.FloatPercentiles[/* fromArray */5](/* array */[
                                        /* tuple */[
                                          25.0,
                                          1.0
                                        ],
                                        /* tuple */[
                                          50.0,
                                          3.0
                                        ],
                                        /* tuple */[
                                          75.0,
                                          10.0
                                        ]
                                      ]))));
              }));
        Jest.test("#hasQuartiles false", (function () {
                return Jest.Expect[/* toEqual */12](false, Jest.Expect[/* expect */0](Value$Shared.FloatPercentiles[/* hasQuartiles */2](Value$Shared.FloatPercentiles[/* fromArray */5](/* array */[
                                        /* tuple */[
                                          25.0,
                                          1.0
                                        ],
                                        /* tuple */[
                                          50.0,
                                          3.0
                                        ],
                                        /* tuple */[
                                          78.0,
                                          10.0
                                        ]
                                      ]))));
              }));
        return Jest.test("#encode", (function () {
                      var json = Json.parseOrRaise(" {\n        \"dataType\": \"floatByPercentile\",\n        \"data\":   { \"25.\": 1.0, \"50.\": 3.0, \"78.\":10.0 }\n      } ");
                      return Jest.Expect[/* toEqual */12](json, Jest.Expect[/* expect */0](Value$Shared.FloatPercentiles[/* encode */8](Value$Shared.FloatPercentiles[/* fromArray */5](/* array */[
                                              /* tuple */[
                                                25.0,
                                                1.0
                                              ],
                                              /* tuple */[
                                                50.0,
                                                3.0
                                              ],
                                              /* tuple */[
                                                78.0,
                                                10.0
                                              ]
                                            ]))));
                    }));
      }));

describe("Value", (function () {
        Jest.test("#encode DateTimePercentiles", (function () {
                var json = Json.parseOrRaise(" {\n        \"dataType\": \"floatByPercentile\",\n        \"data\":   { \"25.\": 1.0, \"50.\": 3.0, \"75.\":10.0 }\n      } ");
                var floatPercentiles = Value$Shared.FloatPercentiles[/* fromArray */5](/* array */[
                      /* tuple */[
                        25.0,
                        1.0
                      ],
                      /* tuple */[
                        50.0,
                        3.0
                      ],
                      /* tuple */[
                        75.0,
                        10.0
                      ]
                    ]);
                var value = /* FloatPercentiles */Block.__(1, [floatPercentiles]);
                return Jest.Expect[/* toEqual */12](json, Jest.Expect[/* expect */0](Value$Shared.encodee(value)));
              }));
        return Jest.test("#decode DateTimePercentiles", (function () {
                      var json = Json.parseOrRaise(" {\n        \"dataType\": \"floatByPercentile\",\n        \"data\":   { \"25.\": 1.0, \"50.\": 3.0, \"75.\":10.0 }\n      } ");
                      var floatPercentiles = Value$Shared.FloatPercentiles[/* fromArray */5](/* array */[
                            /* tuple */[
                              25.0,
                              1.0
                            ],
                            /* tuple */[
                              50.0,
                              3.0
                            ],
                            /* tuple */[
                              75.0,
                              10.0
                            ]
                          ]);
                      var value = /* FloatPercentiles */Block.__(1, [floatPercentiles]);
                      return Jest.Expect[/* toEqual */12](value, Jest.Expect[/* expect */0](Value$Shared.decode(json)));
                    }));
      }));

/*  Not a pure module */
