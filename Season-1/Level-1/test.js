const request = require('supertest');
const { expect } = require('chai');
const app = require('./code');

describe('Level-2 Testing', function() {
    it('Level-2 Testing succeed', function(done) {
        request(app)
            .get('/level-2')
            .query({ number: '1e5' }) // 길이 3, 값 100000 → Success!
            .expect(200)
            .end(function(err, res) {
                if (err) return done(err);
                expect(res.text).to.equal('Success!');
                done();
            });
    });

    it('Level-2 Testing failed', function(done) {
        request(app)
            .get('/level-2')
            .query({ number: '123' }) // 길이 3, 값 123 → Failed!
            .expect(200)
            .end(function(err, res) {
                if (err) return done(err);
                expect(res.text).to.equal('Failed!');
                done();
            });
    });
});
