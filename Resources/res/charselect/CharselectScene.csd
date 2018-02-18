<GameFile>
  <PropertyGroup Name="CharselectScene" Type="Scene" ID="1c049daa-f7f3-4146-891a-74de4f50b3a4" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="2" Speed="1.0000">
        <Timeline ActionTag="308958992" Property="VisibleForFrame">
          <BoolFrame FrameIndex="0" Tween="False" Value="True" />
          <BoolFrame FrameIndex="1" Tween="False" Value="False" />
        </Timeline>
        <Timeline ActionTag="1644708471" Property="Position">
          <PointFrame FrameIndex="0" X="403.0001" Y="291.0002">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="1644708471" Property="VisibleForFrame">
          <BoolFrame FrameIndex="0" Tween="False" Value="True" />
          <BoolFrame FrameIndex="1" Tween="False" Value="True" />
          <BoolFrame FrameIndex="2" Tween="False" Value="False" />
        </Timeline>
        <Timeline ActionTag="1644708471" Property="Alpha">
          <IntFrame FrameIndex="0" Value="250">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
        <Timeline ActionTag="-2110163777" Property="VisibleForFrame">
          <BoolFrame FrameIndex="0" Tween="False" Value="True" />
          <BoolFrame FrameIndex="2" Tween="False" Value="True" />
        </Timeline>
      </Animation>
      <ObjectData Name="Scene" ctype="GameNodeObjectData">
        <Size X="800.0000" Y="600.0000" />
        <Children>
          <AbstractNodeData Name="bg" ActionTag="55817606" Tag="60" IconVisible="False" ctype="SpriteObjectData">
            <Size X="800.0000" Y="600.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="400.0000" Y="300.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.5000" />
            <PreSize X="1.0000" Y="1.0000" />
            <FileData Type="Normal" Path="asset/shared/bg.png" Plist="" />
            <BlendFunc Src="770" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="title_princessselect" ActionTag="1022191821" Tag="61" IconVisible="False" RightMargin="470.0000" BottomMargin="523.0000" ctype="SpriteObjectData">
            <Size X="330.0000" Y="77.0000" />
            <AnchorPoint ScaleY="1.0000" />
            <Position Y="600.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition Y="1.0000" />
            <PreSize X="0.4125" Y="0.1283" />
            <FileData Type="Normal" Path="asset/charselect/title_princessselect.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="popup_1" ActionTag="308958992" Tag="62" IconVisible="False" LeftMargin="380.0003" RightMargin="373.9997" TopMargin="285.9999" BottomMargin="268.0001" ctype="SpriteObjectData">
            <Size X="517.0000" Y="357.0000" />
            <Children>
              <AbstractNodeData Name="char1_btn" ActionTag="-1706714847" Tag="1006" IconVisible="False" LeftMargin="41.0000" RightMargin="-95.0000" TopMargin="-175.5000" BottomMargin="121.5000" TouchEnable="True" FontSize="14" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="-15" Scale9OriginY="-11" Scale9Width="30" Scale9Height="22" OutlineSize="0" ShadowOffsetX="0.0000" ShadowOffsetY="0.0000" ctype="ButtonObjectData">
                <Size X="100.0000" Y="100.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="91.0000" Y="171.5000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="1.9783" Y="3.7283" />
                <PreSize X="2.1739" Y="2.1739" />
                <TextColor A="255" R="65" G="65" B="70" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="char2_btn" ActionTag="-1983845064" Tag="1007" IconVisible="False" LeftMargin="205.9999" RightMargin="-259.9999" TopMargin="-175.5000" BottomMargin="121.5000" TouchEnable="True" FontSize="14" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="-15" Scale9OriginY="-11" Scale9Width="30" Scale9Height="22" OutlineSize="0" ShadowOffsetX="0.0000" ShadowOffsetY="0.0000" ctype="ButtonObjectData">
                <Size X="100.0000" Y="100.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="255.9999" Y="171.5000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="5.5652" Y="3.7283" />
                <PreSize X="2.1739" Y="2.1739" />
                <TextColor A="255" R="65" G="65" B="70" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="char3_btn" ActionTag="-1062706575" Tag="1008" IconVisible="False" LeftMargin="370.9999" RightMargin="-424.9999" TopMargin="-175.5000" BottomMargin="121.5000" TouchEnable="True" FontSize="14" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="-15" Scale9OriginY="-11" Scale9Width="30" Scale9Height="22" OutlineSize="0" ShadowOffsetX="0.0000" ShadowOffsetY="0.0000" ctype="ButtonObjectData">
                <Size X="100.0000" Y="100.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="420.9999" Y="171.5000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="9.1522" Y="3.7283" />
                <PreSize X="2.1739" Y="2.1739" />
                <TextColor A="255" R="65" G="65" B="70" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="403.0003" Y="291.0001" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5038" Y="0.4850" />
            <PreSize X="0.0575" Y="0.0767" />
            <FileData Type="Normal" Path="asset/charselect/popup_princessselect_1.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="popup_2" Visible="False" ActionTag="1644708471" Alpha="250" Tag="63" IconVisible="False" LeftMargin="380.0001" RightMargin="373.9999" TopMargin="285.9998" BottomMargin="268.0002" ctype="SpriteObjectData">
            <Size X="517.0000" Y="357.0000" />
            <Children>
              <AbstractNodeData Name="yes_btn" ActionTag="-1919112154" Tag="73" IconVisible="False" LeftMargin="39.2396" RightMargin="-141.2396" TopMargin="75.3157" BottomMargin="-81.3157" TouchEnable="True" FontSize="14" Scale9Width="1" Scale9Height="1" OutlineSize="0" ShadowOffsetX="0.0000" ShadowOffsetY="0.0000" ctype="ButtonObjectData">
                <Size X="148.0000" Y="52.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="113.2396" Y="-55.3157" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="2.4617" Y="-1.2025" />
                <PreSize X="3.2174" Y="1.1304" />
                <TextColor A="255" R="65" G="65" B="70" />
                <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="back_btn" ActionTag="-749322853" Tag="69" IconVisible="False" LeftMargin="328.5226" RightMargin="-430.5226" TopMargin="74.5000" BottomMargin="-80.5000" TouchEnable="True" FontSize="14" Scale9Width="1" Scale9Height="1" OutlineSize="0" ShadowOffsetX="0.0000" ShadowOffsetY="0.0000" ctype="ButtonObjectData">
                <Size X="148.0000" Y="52.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="402.5226" Y="-54.5000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="8.7505" Y="-1.1848" />
                <PreSize X="3.2174" Y="1.1304" />
                <TextColor A="255" R="65" G="65" B="70" />
                <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="AttributeNode" ActionTag="-1747103687" Tag="1010" IconVisible="True" LeftMargin="304.0000" RightMargin="-258.0000" TopMargin="-210.0000" BottomMargin="256.0000" ctype="SingleNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="304.0000" Y="256.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="6.6087" Y="5.5652" />
                <PreSize X="0.0000" Y="0.0000" />
              </AbstractNodeData>
              <AbstractNodeData Name="NameText" ActionTag="792179082" Tag="1011" IconVisible="False" LeftMargin="353.5000" RightMargin="-399.5000" TopMargin="-224.5000" BottomMargin="247.5000" FontSize="20" LabelText="Text Label" OutlineSize="0" ShadowOffsetX="0.0000" ShadowOffsetY="0.0000" ctype="TextObjectData">
                <Size X="92.0000" Y="23.0000" />
                <AnchorPoint ScaleY="0.5000" />
                <Position X="353.5000" Y="259.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="7.6848" Y="5.6304" />
                <PreSize X="2.0000" Y="0.5000" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="LevelText" ActionTag="54091902" Tag="1012" IconVisible="False" LeftMargin="358.5000" RightMargin="-345.5000" TopMargin="-181.5000" BottomMargin="204.5000" FontSize="20" LabelText="Lv1" HorizontalAlignmentType="HT_Center" OutlineSize="0" ShadowOffsetX="0.0000" ShadowOffsetY="0.0000" ctype="TextObjectData">
                <Size X="33.0000" Y="23.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="375.0000" Y="216.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="8.1522" Y="4.6957" />
                <PreSize X="0.7174" Y="0.5000" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="AtkText" ActionTag="-698749409" Tag="1013" IconVisible="False" LeftMargin="409.5000" RightMargin="-386.5000" TopMargin="-146.5000" BottomMargin="169.5000" FontSize="20" LabelText="40" OutlineSize="0" ShadowOffsetX="0.0000" ShadowOffsetY="0.0000" ctype="TextObjectData">
                <Size X="23.0000" Y="23.0000" />
                <AnchorPoint ScaleY="0.5000" />
                <Position X="409.5000" Y="181.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="8.9022" Y="3.9348" />
                <PreSize X="0.5000" Y="0.5000" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="SkillText" ActionTag="1055300435" Tag="1014" IconVisible="False" LeftMargin="306.5000" RightMargin="-352.5000" TopMargin="-80.5000" BottomMargin="103.5000" FontSize="20" LabelText="Text Label" OutlineSize="0" ShadowOffsetX="0.0000" ShadowOffsetY="0.0000" ctype="TextObjectData">
                <Size X="92.0000" Y="23.0000" />
                <AnchorPoint ScaleY="0.5000" />
                <Position X="306.5000" Y="115.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="6.6630" Y="2.5000" />
                <PreSize X="2.0000" Y="0.5000" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="chara_princessselect" ActionTag="707790892" Tag="1015" IconVisible="True" LeftMargin="140.5000" RightMargin="-94.5000" TopMargin="-118.5000" BottomMargin="164.5000" ctype="SingleNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="140.5000" Y="164.5000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="3.0543" Y="3.5761" />
                <PreSize X="0.0000" Y="0.0000" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="403.0001" Y="291.0002" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5038" Y="0.4850" />
            <PreSize X="0.0575" Y="0.0767" />
            <FileData Type="Normal" Path="asset/charselect/popup_princessselect_2.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="popup_3" Visible="False" ActionTag="-2110163777" Tag="72" IconVisible="False" LeftMargin="377.0000" RightMargin="377.0000" TopMargin="128.5011" BottomMargin="425.4989" ctype="SpriteObjectData">
            <Size X="46.0000" Y="46.0000" />
            <Children>
              <AbstractNodeData Name="start_btn" ActionTag="1807002627" Tag="68" IconVisible="False" LeftMargin="165.9984" RightMargin="-356.9984" TopMargin="342.5000" BottomMargin="-348.5000" TouchEnable="True" FontSize="14" Scale9Width="1" Scale9Height="1" OutlineSize="0" ShadowOffsetX="0.0000" ShadowOffsetY="0.0000" ctype="ButtonObjectData">
                <Size X="237.0000" Y="52.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="284.4984" Y="-322.5000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="6.1847" Y="-7.0109" />
                <PreSize X="5.1522" Y="1.1304" />
                <TextColor A="255" R="65" G="65" B="70" />
                <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="chara_princessselect" ActionTag="-1470185440" Tag="1016" IconVisible="True" LeftMargin="290.0000" RightMargin="-244.0000" TopMargin="172.0000" BottomMargin="-126.0000" ctype="SingleNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="290.0000" Y="-126.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="6.3043" Y="-2.7391" />
                <PreSize X="0.0000" Y="0.0000" />
              </AbstractNodeData>
              <AbstractNodeData Name="NameText" ActionTag="1886562465" Tag="1017" IconVisible="False" LeftMargin="134.0000" RightMargin="-180.0000" TopMargin="-43.5000" BottomMargin="66.5000" FontSize="20" LabelText="Text Label" OutlineSize="0" ShadowOffsetX="0.0000" ShadowOffsetY="0.0000" ctype="TextObjectData">
                <Size X="92.0000" Y="23.0000" />
                <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                <Position X="226.0000" Y="78.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="4.9130" Y="1.6957" />
                <PreSize X="2.0000" Y="0.5000" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="400.0000" Y="448.4989" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.7475" />
            <PreSize X="0.0575" Y="0.0767" />
            <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>