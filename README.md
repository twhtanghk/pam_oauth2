# pam_oauth2
OAuth2 pam and nss module

## Configuration
* update envvironment variables defined in .env
* update host port defined in docker-compose.yml if necessary
* docker-compose -f docker-compose.yml up -d

## ssh connection to container
```
ssh -p 8000 user@localhost
```

## Limitation
Manually create user home directory, chown user1:10000 /home/user1 now and it is not ready to create home directory automatically via pam_mkhomedir.
