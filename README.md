# Primitive Date Database
This database is written on C++ and has 5 simple actions. It can store information about events happened on certain dates. Also you can delete events or whole dates from this database. To see what events are held in the database you can use "**Print**" or "**Find**" commands.
### Add Command
---
Add (Date) (event)
  
Date should be written in following format : yyyy-mm-dd

In case of invalid requests, database will inform you about errors. 
### Del Command
---
Del <Date> to delete the Date from database and all the events, that happened that day
  
Or

Del <Date> <event> to delete one exact event from the following Date.
### Find Command
---
Find <Date> to print all events, happened in that Date.
### Print command
---
Just type Print to see all events with their dates
