FROM nginx:mainline-alpine

ADD ./config/nginx.conf /etc/nginx/nginx.conf

ADD ./ssl/* /etc/ssl/

EXPOSE 443

CMD ["nginx"]
