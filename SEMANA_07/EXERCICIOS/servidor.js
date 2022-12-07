// importa bibliotecas necessárias para criar servidor (express) e se comunicar com database (sqlite3)
const express = require('express');
const hostname = "10.128.65.111";
// cria servidor
const app = express();
// define host e porta do servidor
const port = process.env.PORT || 3000;
// cria objetos para interpretar dados passados em requisições HTTP
const bodyParser = require('body-parser');
const urlencodedParser = bodyParser.urlencoded({ extended: false });
let direcao = [0, 0];
// define que pasta "public" deve ser utilizada como source para página principal (index.html)
app.use(express.static("public"));
// define que utilizaremos json em nossas comunicações
app.use(express.json());
// evita erros de CORS nas requisições
const cors = require("cors");
const corsOptions = {
    origin: '*',
    credentials: true,
    optionSuccessStatus: 200
}
app.use(cors(corsOptions))
let levels = [0, 0, 0, 0, 0, 0, 0, 0]
app.post("/levels/insert", (req, res) => {
    sensors = req.body.sensors
    console.log(sensors);
})
/* DEFINIÇÃO DOS ENDPOINTS */
app.get('/leitura_direcao', (req, res) => {
    res.statusCode = 200;
    res.setHeader('Access-Control-Allow-Origin', '*');
     // Transforma array de últimas leituras em json
    console.log(direcao);
    res.send(JSON.stringify(direcao))
});

app.post('/insere_direcao_gt', urlencodedParser, (req, res) => {
    res.statusCode = 200;
    console.log(req.body)
    res.statusCode = 200;
    let reading = req.body.direcao // Salva dados da requisição em uma variável
    // Salva dados na variável direcao 
    direcao[0] = reading;
    console.log(direcao);
    res.end()
});

app.post('/insere_direcao_rapha', urlencodedParser, (req, res) => {
    res.statusCode = 200;
    console.log(req.body)
    res.statusCode = 200;
    let reading = req.body.direcao
    direcao[1] = reading;
    console.log(direcao);
    res.end()
});
// Inicia o servidor
app.listen(port, hostname, () => {
    console.log(`Server running at http://${hostname}:${port}/`);
});