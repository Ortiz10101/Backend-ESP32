const express = require('express')

const app = express()

require('dotenv').config()
const port = process.env.PORT || 5000

const connectDB = require('./config/db')

connectDB()

//body parser middleware
app.use(express.json())
app.use(express.urlencoded({ extended: false}))

//rutas
app.get('/', (req,res) => {
    res.json({message: 'Lecturas ESP32 consumo Electrico'})
});

const readingsRouter = require('./routes/readings')
app.use('/Potencia/readings', readingsRouter)

app.listen(port, () => console.log(`Server listening on port ${port}`))