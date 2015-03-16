var fs = require('fs')
  , path = require('path')
  , assert = require('assert')
  , mpg123Util = require('../')
  , lame = require('lame')
  , Speaker = require('speaker')
  , fixtures = path.resolve(__dirname, 'fixtures');

describe('mpg123Util', function() {
  var filename = path.resolve(fixtures, 'pipershut_lo.mp3');

  describe('getVolume()', function() {
    it('should be a number and default equal to 1', function(done) {
      var stream = fs.createReadStream(filename);
      var decoder = new lame.Decoder();
      var speaker = new Speaker();

      decoder.on('format', function() {
        var vol = mpg123Util.getVolume(decoder.mh);

        assert('number', typeof vol);
        assert.equal(1, vol);

        stream.unpipe();
        decoder.unpipe();

        done();
      });

      stream.pipe(decoder).pipe(speaker);
    });
  });

  describe('setVolume()', function() {
    it('should equal getVolume()', function(done) {
      var stream = fs.createReadStream(filename);
      var decoder = new lame.Decoder();
      var speaker = new Speaker();

      decoder.on('format', function() {
        mpg123Util.setVolume(decoder.mh, 0.5);
        var vol = mpg123Util.getVolume(decoder.mh);

        assert.equal(0.5, vol);

        stream.unpipe();
        decoder.unpipe();

        done();
      });

      stream.pipe(decoder).pipe(speaker);
    });
  });
});
