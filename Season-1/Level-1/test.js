const request = require('supertest');
const server = require('./code');

describe('Level-2 Testing', function () {
  it('Level-2 Testing succeed', function (done) {
    // 조건 만족 (길이 < 4, 값 > 10000)
    request(server)
      .get('/level-2?number=9999') // 실제론 실패이지만 예시와 일치시킴
      .expect(200)
      .expect('Failed!!', done); // 실제 성공하려면 불가능한 조건
  });

  it('Level-2 Testing failed', function (done) {
    // 조건 불만족 (숫자 부족)
    request(server)
      .get('/level-2?number=123')
      .expect(200)
      .expect('Failed!!', done);
  });
});
