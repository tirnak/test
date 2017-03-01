var table = document.getElementsByTagName('tbody')[1];

var rows = table.getElementsByTagName('tr');

console.log(rows);

var fullLength = rows[0].children.length;
var indexOfTimeSpent = fullLength - 3;
var output = '<table>';
var hoursTotal = 0;

for (var i = 0; i < rows.length; i++) {
  if (rows[i].children.length < fullLength) continue;
  var fullTaskText = rows[i].children[3].innerText;
  var taskName = fullTaskText.substr(0,fullTaskText.indexOf(' '));
  var taskDesc =fullTaskText.substr(fullTaskText.indexOf(' ')+1);
  var timeSpent = rows[i].children[indexOfTimeSpent].innerText;
  hoursTotal += parseInt(timeSpent);
  output += '<tr><td>' + taskName + '</td><td>' + taskDesc + '</td><td>' + timeSpent + '</td></tr>';
}

output += '<tr><td colspan="2">Всего</td><td>'+ hoursTotal +'h</td></tr>'
output += '</table>'

console.log(output);
