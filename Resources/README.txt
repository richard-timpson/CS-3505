Client TODO:
	Peter:
		- List of spreadsheets window on successful login
		- Learn more about ListBox. Is that the way to go when it comes to listing spreadsheets?
		- Initial Connection? Send It has the initial connection before username/password. Will we need to make another connect
	      method that only connects to the address?
		- Passing in an invalid address can take a second before it throws an exception. Should we disable/reenable everything when the client
		  hits the connect button?
	Zach: 
		- Push Administrator GUI as its own solution
	Tyler: 
		- test JSON

Client Completed
	Peter:
		- Address textbox
	Zach:
	Tyler: 

JSON SERIALIZE?
            //var mess = new
            //{
            //    type = ss.sb.ToString(),
            //    cell = "A1",
            //};
            //JsonConvert.SerializeObject(mess);


			Test JSON
			// spreadsheet list
		    {"type":"list","spreadsheets":["hello.sprd","foxy spreadsheet"]}
			
			//Full Send
			{"type": "full send", "spreadsheet": {"A2": "=2*A1+1", "A1": 3}}

			//Error
			{"type" : "error", "code" : 1, "source": ""}


