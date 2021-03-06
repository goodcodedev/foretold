open FC__Base;
open FC;
let make =
  <Div>
    <AppHeader
      links={
        [|
          AppHeader.link(
            ~href="#",
            [|"Public Channels" |> ReasonReact.string|],
          )
          |> ReasonReact.element,
          AppHeader.link(
            ~href="#",
            [|"Entity Explorer" |> ReasonReact.string|],
          )
          |> ReasonReact.element,
        |]
        |> ReasonReact.array
      }
    />
    Example__AppGroupHeader.make
    <Div
      styles=[
        Css.(
          style(
            [
              marginTop(`em(2.)),
              width(`percent(100.)),
              paddingLeft(`em(2.)),
              paddingRight(`em(2.)),
              boxSizing(`borderBox),
            ]
            @ BaseStyles.fullWidthFloatLeft,
          )
        ),
      ]>
      Example__MeasurableIndexPage.make
    </Div>
    <Div
      styles=[
        Css.(
          style(
            [
              marginTop(`em(2.)),
              width(`percent(100.)),
              paddingLeft(`em(2.)),
              paddingRight(`em(2.)),
              boxSizing(`borderBox),
            ]
            @ BaseStyles.fullWidthFloatLeft,
          )
        ),
      ]>
      <Div flexDirection=`row>
        <Div flex=5 styles=[Css.(style([paddingRight(`em(2.0))]))]>
          <Div> Example__MeasurableTopCard.make </Div>
          <Div
            styles=[
              Css.(
                style(
                  [marginTop(`em(2.0))] @ BaseStyles.fullWidthFloatLeft,
                )
              ),
            ]>
            Example__CardMeasurableMeasurements.make
          </Div>
        </Div>
        <Div flex=2> Example__MeasurableTopCard.make </Div>
      </Div>
    </Div>
    <Footer/>
  </Div>;