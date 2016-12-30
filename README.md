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
cannot automatically create home directory via pam_mkhomedir
