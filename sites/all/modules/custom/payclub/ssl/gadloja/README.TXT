Date: Jun 5, 2015
Author: Darwin Betancourt C.
Description: Key and Sign for payclub integration

-----------------------------------------------------------------------

openssl rsa -in gadprivatekey.pem -out gadpublickey.pem -pubout
openssl rsa -in gadprivatesign.pem -out gadpublicsign.pem -pubout

openssl rsa -in gadprivatesign.pem -out gadpublicsign.pem -pubout
openssl rsa -in gadprivatekey.pem -out gadpublickey.pem -pubout
