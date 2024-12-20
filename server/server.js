const express = require('express');
const path = require('path');
const app=express();

const LASTEST_VERSION="1.2";
const PORT=3000;
const bodyParser=require("body-parser");
app.use(bodyParser.urlencoded({extended:false}));
app.use(bodyParser.json());

//app.get('/',(req,res) =>{
//    res.send(`<html><center>hello word!</center></html>`);
//});


app.get('/upgrade',(req,res) =>{
    const currentVersion=req.query.currentVersion;
    const key=req.query.key;
    if(!key||key!="123456"||!currentVersion){
        console.error("Error: Unauthorized access attempt!");
        return res.status(401).json({error:"Error: Unauthorized access attempt!"});
    }
    console.log(currentVersion+":"+LASTEST_VERSION);

    if(currentVersion>=LASTEST_VERSION){
        console.warn("client already have The lastest version!");
        return res.status(200).json({error:"warn:you already have The lastest version!"});
    }
    const filePath=path.join(__dirname,'files',`test${LASTEST_VERSION}.bin`);
    res.download(filePath,'test.bin',(err) =>{
        if(err){
            console.error("Update Cant Sent To Client!");
            return res.status(500).json({error:"Failed to download the update file!"});
        }
        console.log("update send to client successfuly.");
    });
});

app.listen(PORT,() =>{
    console.log(`Server is running at Localhost:${PORT}`);

});