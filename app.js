const express = require('express');
const mysql = require('mysql2');

const bodyParser = require('body-parser');

require('dotenv').config()

const PORT = process.env.PORT || 3050;

const app = express();

var jsonParser = bodyParser.json()
 
// create application/x-www-form-urlencoded parser
var urlencodedParser = bodyParser.urlencoded({ extended: false })

//Mysql
const connection = mysql.createConnection({
    host: process.env.HOST,
    user: process.env.DBUSER,
    password: process.env.PASSWORD,
    database: process.env.DATABASE
});

//Route
app.get('/',(req,res)=>{
    res.sendFile('index.html', { root: __dirname })
})

//All customers
app.get('/GET',(req, res) =>{
    
    const sql = 'SELECT * FROM lecturas_periodicas ORDER BY ID DESC LIMIT 1';
    connection.query(sql,(err,results )=> {
        if (err) throw err;
        if(results.length > 0){
            res.json(results);
        }else{
            res.send('No results');
        }
    });
     
})

app.get('/get24/:date',(req, res) =>{
    const sql = 'SELECT temperatura, vibraciones, humedad, date_format(fecha, "%H:%i") as hora FROM lecturas_periodicas WHERE DATE(FECHA)="'+ req.params.date+'"';
    connection.query(sql,(err,results )=> {
        if (err) throw err;
        if(results.length > 0){
            res.json(results);
        } else{
            res.send('No results');
        }
    });
})

app.get('/getmov24/:date',(req, res) =>{
    const sql = 'select hour(fecha) as hora, count(hour(fecha)) as activaciones from movimientos where date(fecha) = "' + req.params.date + '" group by hour(fecha);';
    connection.query(sql,(err,results )=> {
        if (err) throw err;
        if(results.length > 0){
            res.json(results);
        } else{
            res.send('No results');
        }
    });
})


app.post('/add', urlencodedParser , (req,res)=>{

    const sql = 'INSERT INTO lecturas_periodicas SET ?';

    const lecturaObj = {
        humedad: req.body.humedad,
        temperatura: req.body.temperatura,
        vibraciones: req.body.vibraciones,
    };

    connection.query(sql, lecturaObj, error => {
        if(error) throw error;
        res.send('Lectura creada');
    });
});

app.post('/movimiento', urlencodedParser , (req,res)=>{

    const sql = 'INSERT INTO movimientos () values ()'

    connection.query(sql, error => {
        if(error) throw error;
        res.send('Movimiento creado');
    });
});



//Check connect
connection.connect(error =>{
    if(error) throw error;
    console.log(`Database server running on port ${PORT}!`);
});

app.listen(PORT)