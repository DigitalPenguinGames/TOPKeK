import glob
import xml.etree.ElementTree as ET

regex = "*.tmx"

def main():
	for c in glob.glob(regex):
		output = ""
		tree = ET.parse(c)
		root = tree.getroot()

		width = root.get('width')
		height = root.get('height')

		layer = root.find('layer')
		mapType = layer.find('properties').find('property').get('value')

		#

		if mapType == "outside":
			output += "0 "

			output += width + " " + height + " "

			#

			data = layer.find('data')
			csv = data.text.split(',')

			#

			for x in csv:
				output += str(int(x)-1) + " "


		elif mapType == "dungeon":
			output += "1 "
		elif mapType == "dungeonLight":
			output += "2 "

		

		#
		for shit in root.findall ('objectgroup'):
			if (shit.get('name') == 'Objects'):
				continue
			elif (shit.get('name') == 'Exits'):
				output += str(len(shit.findall('object'))) + " "
				for obj in shit.findall('object'):
					objX = int(obj.get('x')) / int(obj.get('width'))
					objY = (int(obj.get('y'))-1) / int(obj.get('height'))

					# 

					output += str(int(objX)) + " " + str(int(objY)) + " "

					scene = ""
					sceneX = 0
					sceneY = 0
					for prop in obj.find("properties").findall('property'):
						if prop.get('name') == "scene":
							scene = prop.get('value')
						elif prop.get('name') == "x":
							sceneX = prop.get('value')
						elif prop.get('name') == "y":
							sceneY = prop.get('value')

					output += scene + " " + str(sceneX) + " " + str(sceneY) + " "


		name = c
		extension = "scene"
		filename = name[:-4] + '.' + extension
		f = open("../Scenes/"+filename,'w+')
		f.write(output)




		print(output)


if __name__ == '__main__':
	main()