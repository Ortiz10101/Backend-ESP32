const mongoose = require('mongoose');

const readingSchema = new mongoose.Schema({
  firstSensor: {
    type: Number,
    required: true
  },
  secondSensor: {
    type: Number,
    required: true
  },
  thirdSensor: {
    type: Number,
    required: true
  },
  date: {
    type: Date,
    default: Date.now(),
  },
});

const Reading = mongoose.model('Reading', readingSchema);

module.exports = Reading;
