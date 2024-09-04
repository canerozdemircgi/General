from os import fsync
from os.path import isdir
from pathlib import Path
from re import search
from requests import Session
from requests.adapters import HTTPAdapter
from urllib3.util.retry import Retry

location = input('Type location: ').replace('"', '')

headers =\
{
	'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/127.0.0.0 Safari/537.36',
	'Accept-Language': 'en-US,en;q=0.9',
	'Referer': 'https://www.google.com/',
	'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8',
	'Accept-Encoding': 'gzip, deflate, br'
}

retry = Retry\
(
	total = 3,
	backoff_factor = 1,
	status_forcelist = [403, 500, 502, 503, 504],
	allowed_methods = ['HEAD', 'GET', 'PUT', 'DELETE', 'OPTIONS', 'PATCH']
)

adapter = HTTPAdapter(max_retries=retry)
session = Session()
session.headers.update(headers)
session.mount('http://', adapter)
session.mount('https://', adapter)

def print_and_write(message, file):
	print(message)
	file.write(str(message) + '\n')
	file.flush()
	fsync(file.fileno())

def verify_url(address_url, file_url_path, file_log):
	try:
		response = session.get(address_url, timeout=10)
		if response.status_code != 200:
			raise Exception('response.status_code: {}'.format(response.status_code))

		address_url_redirect = response.url
		if address_url == address_url_redirect:
			print('OK\n\tFile: {}\n\tAddress: {}'.format(file_url_path, address_url))
		else:
			print_and_write('Redirected\n\tFile: {}\n\tAddress_Original: {}\n\tAddress_Final: {}'.format(file_url_path, address_url, address_url_redirect), file_log)
	except Exception as ex:
		print_and_write('Error\n\tFile: {}\n\tAddress: {}\n\tException: {}'.format(file_url_path, address_url, ex), file_log)

def main():
	with open('Verify Web.txt', 'w', encoding='utf-8', newline='\n') as file_log:
		if location.endswith('.html'):
			file_url_path = location
			with open(location, encoding='utf-8') as file_bookmark:
				lines_bookmark = [line_bookmark.lower() for line_bookmark in file_bookmark.read().splitlines() if ' href="' in line_bookmark.lower()]
			for line_bookmark in lines_bookmark:
				address_url = search(r' href=[\'"]?([^\'" >]+)', line_bookmark).group(1)
				verify_url(address_url, file_url_path, file_log)
		elif isdir(location):
			for file_url_path in Path(location).rglob('*.url'):
				with open(file_url_path, encoding='utf-8') as file_url:
					data_url = file_url.read().splitlines()
					if len(data_url) != 2:
						print_and_write('Corrupted - File: {}'.format(file_url_path), file_log)
						continue
					address_url = data_url[1].replace('URL=', '')
					verify_url(address_url, file_url_path, file_log)
main()