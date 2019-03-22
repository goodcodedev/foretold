open Utils;
open MomentRe;
open Antd;

module SignUpParams = {
  type state = {
    name: string,
    description: string,
    isPublic: string,
  };
  type fields = [ | `name | `description | `isPublic];
  let lens = [
    (`name, s => s.name, (s, name) => {...s, name}),
    (
      `description,
      s => s.description,
      (s, description) => {...s, description},
    ),
    (`isPublic, s => s.isPublic, (s, isPublic) => {...s, isPublic}),
  ];
};

module SignUpForm = ReForm.Create(SignUpParams);

let showForm = (~form: SignUpForm.state, ~handleSubmit, ~handleChange) =>
  <form onSubmit={ReForm.Helpers.handleDomFormSubmit(handleSubmit)}>
    <Form>
      <Form.Item>
        {"Channel Name" |> ste |> E.React.inH3}
        <Input
          value={form.values.name}
          onChange={ReForm.Helpers.handleDomFormChange(handleChange(`name))}
        />
      </Form.Item>
      <Form.Item>
        {"Description" |> ste |> E.React.inH3}
        <Input
          value={form.values.description}
          onChange={
            ReForm.Helpers.handleDomFormChange(handleChange(`description))
          }
        />
      </Form.Item>
      <Form.Item>
        {"Make Public?" |> ste |> E.React.inH3}
        <AntdSwitch
          checked={form.values.isPublic == "TRUE"}
          onChange={e => handleChange(`isPublic, e ? "TRUE" : "FALSE")}
        />
      </Form.Item>
      <Form.Item>
        <Button _type=`primary onClick={_ => handleSubmit()}>
          {"Submit" |> ste}
        </Button>
      </Form.Item>
    </Form>
  </form>;