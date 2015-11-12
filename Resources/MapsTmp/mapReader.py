import glob
import xml.etree.ElementTree as ET
import os

regex = "*.tmx"

def main():
	for c in glob.glob(regex):
		print(c)
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
				output += "Objects "
				numberOfProps = len(shit.findall('object'))
				output += str(numberOfProps) + " "
				for prop in shit.findall('object'):
					gid = prop.get('gid')
					x = prop.get('x')
					y = prop.get('y')
					output += gid + " " + x + " " + y + " "

				
			elif (shit.get('name') == 'Exits'):
				output += "Exits "
				output += str(len(shit.findall('object'))) + " "
				for obj in shit.findall('object'):
					gid = int(obj.get('gid'))
					objX = float(obj.get('x'))
					objY = float(obj.get('y'))-16

					# 

					output += str(float(objX)) + " " + str(float(objY)) + " "

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
					if (mapType == "dungeon" or mapType == "dungeonLight"):
						output += str(gid) + " "
			elif (shit.get('name') == 'Texts'):
				output += "Texts "
				numberOfProps = len(shit.findall('object'))
				output += str(numberOfProps) + " "
				for prop in shit.findall('object'):
					gid = prop.get('gid')
					x = prop.get('x')
					y = prop.get('y')
					textkey = obj.find("properties").find('property').get('textkey')
					output += gid + " " + x + " " + y + " " + textkey + " "

			elif (shit.get('name') == 'Enemies'):
				output += "Enemies "
				numberOfEnemies = len(shit.findall('object'))
				output += str(numberOfEnemies) + " "
				for prop in shit.findall('object'):
					gid = prop.get('gid')
					x = prop.get('x')
					y = prop.get('y')
					output += gid + " " + x + " " + y  + " "
			elif (shit.get('name') == 'Drops'):
				output += "Drops "
				numberOfDrops = len(shit.findall('object'))
				output += str(numberOfDrops) + " "
				for prop in shit.findall('object'):
					gid = prop.get('gid')
					x = prop.get('x')
					y = prop.get('y')
					output += gid + " " + x + " " + y  + " "

		output += "finish "

		name = c
		extension = "scene"
		filename = name[:-4] + '.' + extension
		f = open(os.path.dirname(os.path.realpath(__file__)) + "/../Scenes/"+filename,'w+')
		f.write(output)




		print(output)


if __name__ == '__main__':
	main()