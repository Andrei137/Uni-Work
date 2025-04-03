WScript.Echo('You have been hacked!');
WScript.Echo('I hope you did not run this on your own PC...');
var f = 'Facultatea';
var mi = 'de Matematica si Informatica';
var unibuc = 'Universitatea din Bucuresti';
var curs = 'Curs Info anul 3';
var minciuna = 'Acesta este un malware. Dispozitivul este compromis';
var adevar = 'Stringul anterior este o minciuna';
try {
    var obj = new ActiveXObject('Scripting.FileSystemObject');
    var out = obj.OpenTextFile('./fmi.txt', 2, true, 0);
    out.WriteLine('Bun venit la acest laborator :)');
    out.Close();
    var fle = obj.GetFile('./fmi.txt');
    fle.attributes = 2
} catch (err) {
    WScript.Echo('Do not worry. Ghosts do not exist!')
}