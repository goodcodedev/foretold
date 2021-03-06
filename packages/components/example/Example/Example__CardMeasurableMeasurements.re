open FC;
open Base;

let pastTime = 1483232400;
let format_standard = "LLL";
/* let format = MomentRe.Moment.format;
   let format_simple = "L";
   let goFormat_simple = format(format_simple); */

let dist: Stats.dist = {
  xs: ExampleCdfs.Example1.xs,
  ys: ExampleCdfs.Example1.ys,
};

let row =
  <Table.RowLink onClick={_ => Js.log("Row Clicked")}>
    <Table.Cell
      flex=2
      styles=[
        Css.(style([paddingTop(`em(0.6)), paddingBottom(`em(0.0))])),
      ]>
      <FC__CdfChart__Plain
        data={"xs": dist.xs, "ys": dist.ys}
        minX=2.0
        color={`hex("#d9dcdf")}
        maxX=12.0
      />
    </Table.Cell>
    <Table.Cell
      flex=1
      styles=[
        Css.(style([paddingTop(`em(0.2)), paddingBottom(`em(0.3))])),
      ]>
      <StatSummary cdf={xs: dist.xs, ys: dist.ys} />
    </Table.Cell>
    <Table.Cell
      flex=1
      styles=[
        Css.(style([paddingTop(`em(0.7)), paddingBottom(`em(0.5))])),
      ]>
      <FC__AgentLink> {"Roger Adams" |> ReasonReact.string} </FC__AgentLink>
    </Table.Cell>
    <Table.Cell
      flex=1
      styles=[
        Css.(style([paddingTop(`em(0.7)), paddingBottom(`em(0.5))])),
      ]>
      <span className=Css.(style([color(FC__Colors.textMedium)]))>
        {
          MomentRe.momentWithUnix(pastTime)
          |> MomentRe.Moment.format(format_standard)
          |> ReasonReact.string
        }
      </span>
    </Table.Cell>
  </Table.RowLink>;

let make =
  <PageCard>
    {
      PageCard.header(
        <Div>
          <Div
            styles=[
              Css.style([
                BaseStyles.floatLeft,
                Css.padding3(~top=`em(0.2), ~bottom=`em(0.0), ~h=`em(1.5)),
              ]),
            ]>
            <Tab isActive=true> {"Predictions" |> ReasonReact.string} </Tab>
            <Tab isActive=false> {"Settings" |> ReasonReact.string} </Tab>
          </Div>
        </Div>,
      )
    }
    {
      PageCard.header(
        <Div>
          <Div float=`right>
            {
              PaginationButtons.make({
                currentValue: Range(3, 10),
                max: 100,
                pageLeft: {
                  isDisabled: false,
                  onClick: _ => (),
                },
                pageRight: {
                  isDisabled: true,
                  onClick: _ => (),
                },
              })
            }
          </Div>
        </Div>,
      )
    }
    <Div styles=[Css.style(BaseStyles.fullWidthFloatLeft)]>
      <Table.HeaderRow>
        <Table.Cell
          flex=2
          styles=[
            Css.(style([paddingTop(`em(0.7)), paddingBottom(`em(0.7))])),
          ]>
          {"Prediction Distribution" |> ReasonReact.string}
        </Table.Cell>
        <Table.Cell
          flex=1
          styles=[
            Css.(style([paddingTop(`em(0.7)), paddingBottom(`em(0.7))])),
          ]>
          {"Prediction Value" |> ReasonReact.string}
        </Table.Cell>
        <Table.Cell
          flex=1
          styles=[
            Css.(style([paddingTop(`em(0.7)), paddingBottom(`em(0.7))])),
          ]>
          {"Agent" |> ReasonReact.string}
        </Table.Cell>
        <Table.Cell
          flex=1
          styles=[
            Css.(style([paddingTop(`em(0.7)), paddingBottom(`em(0.7))])),
          ]>
          {"Time" |> ReasonReact.string}
        </Table.Cell>
      </Table.HeaderRow>
      row
      row
      row
      row
      row
      row
      row
      row
    </Div>
  </PageCard>;