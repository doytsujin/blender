import bpy
from bpy.props import *
from .. base import BParticlesNode
from .. node_builder import NodeBuilder

class ChangeParticleVelocityNode(bpy.types.Node, BParticlesNode):
    bl_idname = "bp_ChangeParticleVelocityNode"
    bl_label = "Change Particle Velocity"

    mode = EnumProperty(
        name="Mode",
        items=[
            ('SET', "Set", "Set a specific velocity", 'NONE', 0),
            ('RANDOMIZE', "Randomize", "Apply some randomization to the velocity", 'NONE', 1),
        ],
        update= BParticlesNode.sync_tree,
    )

    def declaration(self, builder: NodeBuilder):
        if self.mode == 'SET':
            builder.fixed_input("velocity", "Velocity", "Vector")
        elif self.mode == 'RANDOMIZE':
            builder.fixed_input("randomness", "Randomness", "Float", default=0.5)

        builder.execute_output("execute", "Execute")

    def draw(self, layout):
        layout.prop(self, "mode", text="")
