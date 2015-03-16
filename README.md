# node-mpg123-util

## Example

``` javascript
var fs = require('fs')
  , lame = require('lame')
  , Speaker = require('speaker');

var stream = fs.createReadStream('/path/to/some.mp3')
  , decoder = new lame.Decoder()
  , speaker = new Speaker();

decoder.on('format', function() {
  mpg123Util.setVolume(decoder.mh, 0.5);
  var vol = mpg123Util.getVolume(decoder.mh);
  console.log(vol);
});

stream.pipe(decoder).pipe(speaker);
```
