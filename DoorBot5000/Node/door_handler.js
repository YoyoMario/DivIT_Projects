const express = require('express');
const app = express();
const bodyParser = require('body-parser');
const axios = require('axios');

const webhookUrl = 'https://hooks.slack.com/services/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';//'https://hooks.slack.com/services/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';
const unlockDoorMessage = '[{"type": "section","text": {"type": "mrkdwn","text": "Unlocking doors!\nHello dear employee! Press this magical button to enter!"}},{"type": "divider"},{"type": "actions","elements": [{"type": "button","text": {"type": "plain_text","text": "Unlock Door","emoji": true},"value": "click_me_123"}]}]';

const header = {
	'Content-Type': 'application/json'
}

var unlockDoorState = 'NO';

app.use(bodyParser.json()); // support json encoded bodies
app.use(bodyParser.urlencoded({ extended: false })); // support encoded bodies

app.get('/doorbot', function(request, response){
	response.send(unlockDoorState);
	unlockDoorState = 'NO';
});

app.post('/doorbot', function(request, response){
	if(request.body && request.body.payload){
		var data = JSON.parse(request.body.payload);

		if(data.type !== 'block_actions'){
			response.sendStatus(200);
			return;
		}

		var pressedButton = data.actions[0].text.text;
		if(pressedButton === 'Unlock Door')
		{
			unlockDoorState = 'YES';			
		}
	}

	response.sendStatus(200);
});

app.listen(3001, function(){
	console.log('Server started on port 3001');
	axios.post(webhookUrl, {
		blocks: unlockDoorMessage
	});
});