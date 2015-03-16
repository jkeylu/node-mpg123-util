var binding = require('bindings')('binding');

exports.setVolume = binding.mpg123_volume;
exports.getVolume = binding.mpg123_getvolume;
