
var _runScript = function(file) {
    var exec = require('child_process').exec;
    child= exec('node '+file,(error, stdout, stderr) => {
        if (error) {
            throw error;
        }
        console.log(stdout);
    });
}
var _isEnable = function(dir, file) {
    var fs = require('fs'); 
    var xml2js = require('./xml2js/node_modules/xml2js'); 
    var parser = new xml2js.Parser();  
    fs.readFile(file, function(err, data) {
    parser.parseString(data, function (err, result) {
        if(result.suite.disable=="true") {
            console.log(file + " is disabled");
            return false;
        }
        else {
            _runScript(dir + '/' + result.suite.test[0].execution);
            return true;
        }
    });
});
};
var _getAllFilesFromFolder = function(dir) {

    var filesystem = require("fs");
    var results = [];

    filesystem.readdirSync(dir).forEach(function(file) {

        file = dir+'/'+file;
        var stat = filesystem.statSync(file);

        if (stat && stat.isDirectory()) {
            results = results.concat(_getAllFilesFromFolder(file))
        }
        else {
            if(file.split('.').pop()=='xml') {
                _isEnable(dir, file);
            }
            results.push(file);
        }
    });
    return results;
};
var list = _getAllFilesFromFolder('D:/Projects/trs/jtrs/Tests');