const express = require('express')
const router = express.Router()
const Reading = require('../models/sensor.model')

router.get('/', async (req, res) => {
    try {
        const readings = await Reading.find()
        res.json({success: true, data: readings})
    } catch (err) {
        console.log(err)
        res.status(500).json({ success: false, error: "Something went wrong"})
    }
})
//una sola lectura
router.get('/:id', async (req,res) => {
    try {
        const reading = await Reading.findById(req.params.id);
        res.json({ success: true, data: reading });
    } catch (err) {
        console.log(err);
        res.status(500).json({ success: false, error: 'Something went wrong' });
    }
})

//Add SCT013 reading
router.post('/', async (req, res) => {
    const reading = new Reading({
      firstSensor: req.body.firstSensor,
      secondSensor: req.body.secondSensor,
      thirdSensor: req.body.thirdSensor,
      date: Date.now() - 21600000
    });
  
    try {
      const savedReading = await reading.save();
      res.json({ success: true, data: savedReading });
    } catch (err) {
      console.log(err);
      res.status(500).json({ success: false, error: 'Something went wrong' });
    }
  });

module.exports = router;