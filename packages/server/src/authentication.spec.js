const authentication = require('./authentication');

describe('authentication', () => {
  it('class should be object', () => {
    expect(authentication).toBeInstanceOf(Object);
  });
  it('getToken', () => {
    expect(authentication.getQueryToken).toBeInstanceOf(Function);
  });
  it('authentication', () => {
    expect(authentication.authentication).toBeInstanceOf(Function);
  });
});
